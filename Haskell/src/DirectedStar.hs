{-# LANGUAGE DatatypeContexts #-}

module DirectedStar where
import qualified Data.Vector.Storable as V

data Graph a w = Graph 
  { arch_weights :: V.Vector w
  , from_tos     :: V.Vector (a, a)
  , nodes        :: V.Vector a
  } -- deriving (Eq, Show)
