module Menu where

import Prelude
import Affjax as AX
import Affjax.ResponseFormat as AXRF
import Data.Argonaut.Core (Json)
import Data.Argonaut.Decode (JsonDecodeError, decodeJson, parseJson)
import Data.Argonaut.Decode.Combinators ((.:))
import Data.Either (Either, hush)
import Data.List (List, toUnfoldable)
import Data.Maybe (Maybe(..))
import Effect.Aff.Class (class MonadAff)
import Effect.Console (log)
import Halogen as H
import Halogen.HTML as HH
import Halogen.HTML.Properties as HP

type Link
  = { name :: String, path :: String }

type Info
  = { services ∷ List Link }

decodeInfo :: Json -> Either JsonDecodeError Info
decodeInfo json = do
  x ← decodeJson json
  services ← x .: "services"
  pure { services }

linksFromResponse ∷ ∀ e r. Either e { body ∷ String | r } → Maybe (List Link)
linksFromResponse response = do
  responseBody ← map _.body (hush response)
  json ← hush (parseJson responseBody)
  info ← hush (decodeInfo json)
  pure info.services

type State
  = { loading ∷ Boolean
    , links ∷ List Link
    }

initialState :: State
initialState =
  { loading: true
  , links: mempty
  }

data Action
  = Initialize
  | SetLinks (List Link)

component :: forall query input output m. MonadAff m => H.Component HH.HTML query input output m
component =
  H.mkComponent
    { initialState: const initialState
    , render
    , eval:
        H.mkEval
          $ H.defaultEval
              { handleAction = handleAction
              , initialize = Just Initialize
              }
    }

handleAction :: forall output m. MonadAff m => Action -> H.HalogenM State Action () output m Unit
handleAction = case _ of
  Initialize → do
    response <- H.liftAff $ AX.get AXRF.string ("http://localhost:3000/api/info")
    case linksFromResponse response of
      Just links → handleAction (SetLinks links)
      Nothing → H.liftEffect $ log $ "could not decode info from: " <> show (linksFromResponse response)
  SetLinks links → H.put { loading: false, links }

render :: forall m. State -> H.ComponentHTML Action () m
render state = HH.ul_ (toUnfoldable (map createLink state.links))
  where
  createLink ∷ ∀ a b c. Link → H.ComponentHTML a b c
  createLink link =
    HH.li_
      [ HH.a [ HP.href link.path ] [ HH.text link.name ] ]
