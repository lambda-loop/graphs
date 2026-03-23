
module AdjacencyList where

import qualified Data.Vector as V
import qualified Data.Set as S

newtype Graph a = Graph (V.Vector (S.Set Int))
  deriving (Eq, Show)

mkGraph :: Graph a
mkGraph = Graph (V.empty)






