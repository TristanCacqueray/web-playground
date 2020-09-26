{-# LANGUAGE DeriveGeneric #-}

module HaskellWeb.Types
  ( Link (..),
    Info (..),
    Auth (..),
  )
where

import Data.Aeson
import Data.Text (Text, unpack)
import GHC.Generics

data Link = Link
  { name :: String,
    path :: String
  }
  deriving (Generic, Show)

instance ToJSON Link

data Info = Info
  {services :: [Link]}
  deriving (Generic, Show)

instance ToJSON Info

data Auth = Auth
  { login :: Text,
    password :: Text
  }
  deriving (Generic)

instance Show Auth where
  show (Auth login' _password) = "Auth " <> unpack login' <> " ***"

instance FromJSON Auth
