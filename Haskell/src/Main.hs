
module Main (main) where

import qualified Data.Map as M
import qualified Data.Set as S

import Prelude hiding (interact)
import Graph
import Data.IORef

program :: IORef (Graph Int) -> IO ()
program g_ref = do
  putStrLn menu
  mx <- interact 
  case mx of
    Nothing -> print "Wrong input. try again"
    Just option -> 
      case option of
        Insert  -> undefined
        Remove  -> g_ref `modifyIORef` id
        Print   -> print =<< readIORef g_ref         
        Example -> g_ref `modifyIORef` id






main :: IO ()
main = do 
  g_ref <- newIORef mkGraph
  program g_ref

interact :: IO (Maybe Action)
interact = do 
  option::Int <- read <$> getLine
  pure $ case option of
    1 -> Just Insert
    2 -> Just Remove
    3 -> Just Print
    4 -> Just Example
    _ -> Nothing

data Action 
  = Insert 
  | Remove 
  | Print 
  | Example
  deriving (Eq, Show)

menu :: String
menu = " # options: \n" ++
       " 1 insert   \n" ++ 
       " 2 remove   \n" ++ 
       " 3 print    \n" ++
       " 4 example   "
 

-- Crie um programa para criação e manipulação de
-- um grafo simples, 
-- incluindo as 
  -- funções de inserir vértice, 
  -- excluir vértice 
  -- imprimir grafo. 
-- instância do primeiro exemplo desta aula.
