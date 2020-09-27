module Main exposing (main)

import Browser
import Element exposing (..)
import Http
import Json.Decode exposing (Decoder, field, list, map2, string)



-- MAIN


main : Program () Model Msg
main =
    Browser.document
        { init = init
        , view = view
        , update = update
        , subscriptions = subscriptions
        }


subscriptions : Model -> Sub Msg
subscriptions _ =
    Sub.none



-- MODEL


type Model
    = Failure
    | Loading
    | Success (List Service)


init : () -> ( Model, Cmd Msg )
init _ =
    ( Loading, getServices )



-- UPDATE


type Msg
    = GotServices (Result Http.Error (List Service))


update : Msg -> Model -> ( Model, Cmd Msg )
update msg model =
    case msg of
        GotServices result ->
            case result of
                Ok url ->
                    ( Success url, Cmd.none )

                Err _ ->
                    ( Failure, Cmd.none )



-- VIEW


view : Model -> Browser.Document Msg
view model =
    { title = "Example"
    , body =
        [ layout
            []
            (viewMenu model)
        ]
    }


viewMenu model =
    case model of
        Failure ->
            text "Oops!"

        Loading ->
            text "Loading..."

        Success services ->
            let
                linkService service =
                    link [] { url = service.path, label = text service.name }
            in
            column [] <| List.map linkService services



-- HTTP


getServices : Cmd Msg
getServices =
    Http.get { url = "http://localhost:3000/api/info", expect = Http.expectJson GotServices servicesDecoder }


type alias Service =
    { name : String, path : String }


serviceDecoder : Decoder Service
serviceDecoder =
    map2 Service (field "name" string) (field "path" string)


servicesDecoder : Decoder (List Service)
servicesDecoder =
    field "services" (list serviceDecoder)
