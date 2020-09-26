{-# LANGUAGE DeriveGeneric #-}

module HaskellWeb.Types
  ( Link (..),
    Info (..),
  )
where

import Data.Aeson
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
