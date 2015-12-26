import Data.List.Split

surfaceAreaElems :: [Integer] -> [Integer]
surfaceAreaElems (l:w:h:_) = [l*w, w*h, h*l]
surfaceAreaElems _ = []

amt :: [[Integer]] -> [Integer]
amt [] = []
amt (x:xs) = ((sum . map (2*) $ sae) + minimum sae) : amt xs
        where sae = surfaceAreaElems x

ints :: [[String]] -> [[Integer]]
ints = map (map (read :: String -> Integer))

dims :: [String] -> [[String]]
dims = map (splitOn "x")

main :: IO ()
main = do
    input <- readFile "input.txt"
    print . sum . amt . ints . dims $ lines input
