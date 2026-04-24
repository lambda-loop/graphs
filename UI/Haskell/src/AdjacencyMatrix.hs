
module AdjacencyMatrix where

-- import Control.Concurrent.STM
import qualified Data.Vector as V

newtype Graph a = Graph (V.Vector (V.Vector Int))
  deriving (Eq, Show)

mkGraph :: Graph a
mkGraph = Graph (V.empty)



-- show?



