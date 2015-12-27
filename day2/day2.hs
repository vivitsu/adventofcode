import Data.List.Split

volume :: [Integer] -> Integer
volume (l:w:h:_) = l*w*h
volume _ = 0

perimeterElems :: [Integer] -> [Integer]
perimeterElems (l:w:h:_) = [2*l+2*w, 2*w+2*h, 2*h+2*l]
perimeterElems _ = []

surfaceAreaElems :: [Integer] -> [Integer]
surfaceAreaElems (l:w:h:_) = [l*w, w*h, h*l]
surfaceAreaElems _ = []

ribbon :: [[Integer]] -> [Integer]
ribbon = map (\ x -> minimum (perimeterElems x) + volume x)

amt :: [[Integer]] -> [Integer]
amt [] = []
amt (x:xs) = ((sum . map (2*) $ sae) + minimum sae) : amt xs
        where sae = surfaceAreaElems x

ints :: [[String]] -> [[Integer]]
ints = map (map (read :: String -> Integer))

dims :: [String] -> [[String]]
dims = map (splitOn "x")

printWrappingPaper :: String -> IO ()
printWrappingPaper = print . sum . amt . ints . dims . lines

printRibbon :: String -> IO ()
printRibbon = print . sum . ribbon . ints . dims . lines

main :: IO ()
main = do
    input <- readFile "input.txt"
    _ <- printWrappingPaper input
    printRibbon input
