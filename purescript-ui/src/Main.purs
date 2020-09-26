module Main where

import Prelude
import Effect (Effect)
import Halogen as H
import Halogen.Aff as HA
import Halogen.HTML as HH
import Halogen.VDom.Driver (runUI)

main :: Effect Unit
main =
  HA.runHalogenAff do
    body <- HA.awaitBody
    runUI component unit body

component =
  H.mkComponent
    { initialState
    , render
    , eval: H.mkEval $ H.defaultEval
    }
  where
  initialState _ = 0

  render state =
    HH.div_ [ HH.text "Hello!"]
