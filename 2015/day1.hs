import Data.List

drop' :: [(Integer, Integer)] -> [(Integer, Integer)]
drop' = dropWhile g
    where g (x, _) = x /= (-1)

count' :: String -> [(Integer,Integer)]
count' = foldl' f [(0,0)]
    where f l@((x,y):_) a = if a == '(' then (x+1,y+1):l else (x-1,y+1):l
          f [] _ = []

count :: String -> Integer
count = foldr f 0
    where f a b = if a == '(' then b+1 else b-1

main :: IO ()
main = do
    input <- readFile "day1_input.txt"
    print . snd . head . drop' . reverse . count' $ input
