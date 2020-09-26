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

import HaskellWeb.Types
import Web.Scotty

fakeInfo :: Info
fakeInfo = Info [Link "gerrit" "/r", Link "etherpad" "/etherpad"]

run :: IO ()
run = scotty 3000 $ do
  get "/api/info" $ do
    json fakeInfo
