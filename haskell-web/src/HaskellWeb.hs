{- |
Copyright: (c) 2020 Tristan Cacqueray
SPDX-License-Identifier: Apache-2.0
Maintainer: Tristan Cacqueray <tdecacqu@redhat.com>

See README for more info
-}

module HaskellWeb
       ( someFunc
       ) where


someFunc :: IO ()
someFunc = putStrLn ("someFunc" :: String)
