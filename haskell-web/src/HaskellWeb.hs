{-# LANGUAGE OverloadedStrings #-}

-- |
-- Copyright: (c) 2020 Tristan Cacqueray
-- SPDX-License-Identifier: Apache-2.0
-- Maintainer: Tristan Cacqueray <tdecacqu@redhat.com>
--
-- See README for more info
module HaskellWeb
  ( run,
  )
where

import Data.Text.Lazy (fromStrict)
import HaskellWeb.Auth as Auth
import HaskellWeb.Types
import Network.HTTP.Types.Status (status404)
import Network.Wai.Middleware.Cors (simpleCors)
import Web.Scotty

fakeInfo :: Info
fakeInfo = Info [Link "gerrit" "/r", Link "etherpad" "/etherpad"]

runScotty :: Signer -> IO ()
runScotty signer = scotty 3000 $ do
  middleware simpleCors
  get "/api/info" $ do
    json fakeInfo
  post "/api/auth" $ do
    auth <- jsonData
    case checkAuth signer (User (login auth)) (Password (password auth)) of
      Just token -> text (fromStrict token)
      Nothing -> status status404

run :: IO ()
run = Auth.createSigner >>= runScotty
