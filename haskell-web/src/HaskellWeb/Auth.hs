{-# LANGUAGE OverloadedStrings #-}

module HaskellWeb.Auth
  ( User (..),
    Password (..),
    createSigner,
    checkAuth,
    checkToken,

    -- * Re-export
    Signer,
  )
where

import Data.Text (Text)
import Web.JWT

newtype User = User Text

newtype Password = Password Text

createSigner :: IO Signer
createSigner = pure (hmacSecret "secret-key")

createToken :: Signer -> User -> Text
createToken key (User user) = encodeSigned key mempty (createClaim user)
  where
    createClaim :: Text -> JWTClaimsSet
    createClaim user' = mempty {iss = stringOrURI user'}

checkAuth :: Signer -> User -> Password -> Maybe Text
checkAuth signer (User user) (Password password)
  | user == "admin" && password == "admin" = Just (createToken signer (User "admin"))
  | user /= "admin" = Just (createToken signer (User user))
  | otherwise = Nothing

checkToken :: Signer -> Text -> Maybe User
checkToken signer tokenText =
  do
    token <- decodeAndVerifySignature signer tokenText
    user <- iss (claims token)
    pure $ User (stringOrURIToText user)
