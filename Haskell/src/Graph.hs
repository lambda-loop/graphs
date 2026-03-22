{-# LANGUAGE DatatypeContexts #-}

module Graph where

import qualified Data.Map as M
import qualified Data.Set as S

newtype Ord a => Graph a = 
  Graph (M.Map a (S.Set a))
  deriving (Eq, Show)

mkGraph :: Ord a => Graph a
mkGraph = Graph M.empty
  
insertNode :: Ord a => Graph a -> a -> Graph a
insertNode (Graph m) x = Graph $ 
  M.insert x S.empty m

removeNode :: Ord a => Graph a -> a -> Graph a
removeNode (Graph m) k = Graph $ 
  let s  = m M.! k
      xs = S.toList s
      release x m_ = M.adjust 
        (\s_ -> S.delete k s_) x m_
      m' = foldr release m xs
  in M.delete k m'

insertEdge :: Ord a => Graph a -> (a, a) -> Graph a
insertEdge (Graph m) (from, to) = Graph $ 
  m |> M.adjust (S.insert to) from
    |> M.adjust (S.insert from) to

removeEdge :: Ord a => Graph a -> (a, a) -> Graph a
removeEdge (Graph m) (from, to) = Graph $ 
  m |> M.adjust (S.delete to) from
    |> M.adjust (S.delete from) to


(|>) = flip ($)
