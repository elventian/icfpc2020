import System.Environment
import Network.HTTP.Simple
import Data.ByteString.Lazy.UTF8 as BLU hiding (length, span, splitAt, lines, take, foldl)
import Control.Exception
import Data.Char
import System.IO.Unsafe
import Data.List (intersperse)
import Data.IntMap (IntMap)
import qualified Data.IntMap as IntMap
import Control.Monad
import Debug.Trace


send url msg = do
    request' <- parseRequest ("POST " ++ url)
    putStrLn $ "Sending message: " ++ msg
    let request = setRequestBodyLBS (BLU.fromString msg) request'
    response <- httpLBS request
    let statuscode = show (getResponseStatusCode response)
        strResp = BLU.toString (getResponseBody response)
    case statuscode of
        "200" -> do putStrLn ("Server response: " ++ strResp)
                    putStrLn $ prettyDemodulate ExNum strResp
        _ -> putStrLn ("Unexpected server response:\nHTTP code: " ++ statuscode ++ "\nResponse body: " ++ strResp)
    return $ fst$demodulate strResp


findShId r (BPart "cons_2" [h,t]) = if role==r then (shid, pos) else findShId r t 
    where role = evalBlock' $BApp (BName "car") $ BApp (BName "car") h
          shid = evalBlock' $BApp (BName "car") $ BApp (BName "cdr") $ BApp (BName "car") h
          pos = evalBlock' $BApp (BName "car") $ BApp (BName "cdr") $ BApp (BName "cdr") $ BApp (BName "car") h
findShId r s = error $ show s

loop r url key  = do
    let stage = evalBlock' $ BApp (BName "car") $ BApp (BName "cdr") r
    let role = evalBlock' $ BApp (BName "car") $ BApp (BName "cdr") $BApp (BName "car") $ BApp (BName "cdr") $ BApp (BName "cdr") r
    let shipsnadcommands = evalBlock' $ BApp (BName "car") $ BApp (BName "cdr") $ BApp (BName "cdr") $BApp (BName "car") $ BApp (BName "cdr") $ BApp (BName "cdr") $ BApp (BName "cdr") r
    let (shid, pos) = findShId role shipsnadcommands
    let (BPart "cons_2" [BNum x, BNum y]) = pos
    let (BNum rv) = role
    let (eid, epos) = findShId (BNum (1-rv)) shipsnadcommands
    let (BPart "cons_2" [BNum ex, BNum ey]) = epos
    if stage == BNum 2
    then return ()
    else do let BMod mes = evalBlock' $  BApp (BName "mod") $ BList [BNum 4, BNum key, BList[BList[BNum 0, shid, (BPart "cons_2" [BNum (if abs x > abs y then (-x `div` (abs x)) else 0),BNum (if abs y > abs x then (-y `div` (abs y)) else 0)])],
                                                                                             BList [BNum 2, shid, epos, BNum 5]
                                                                                            ]]
            r1 <- send url mes
            loop r1 url key

main = catch (
    do  
        args <- getArgs
        putStrLn ("ServerUrl: " ++ args!!0 ++ "; PlayerKey: " ++ args!!1)
        let BMod mes = evalBlock' $  BApp (BName "mod") $ BList [BNum 2, BNum (read$args!!1), BNil]
        --r <- send (args!!0) (args!!1)
        r <- send (args!!0 ++ "/aliens/send") mes
        let BMod mes1 = evalBlock' $  BApp (BName "mod") $ BList [BNum 3, BNum (read$args!!1), BList[BNum 256, BNum 5, BNum 13, BNum 1]]
        r <- send (args!!0 ++ "/aliens/send") mes1
        
        loop r (args!!0 ++ "/aliens/send")  (read$args!!1)
        
        
        return ()

    ) handler
    where
        handler :: SomeException -> IO ()
        handler ex = putStrLn $ "Unexpected server response:\n" ++ show ex
        

modulate :: Int -> String
modulate x = let ax = abs x
                 f 0 = ""
                 f x = f(x `div` 2) ++ show (x `mod` 2)
                 s = f ax
                 al = length s
                 l4 = (al-1) `div` 4  + 1
             in (if (x >= 0) then "01" else "10") ++ (replicate l4 '1') ++ (replicate (l4*4-al+1) '0') ++ s
             
demodulate' s = let (lpart, '0':vpart) = span (=='1') s
                    (vpart', rest) = splitAt (4 * length lpart) vpart
                    f a [] = a
                    f a ('0':xs) = f (2*a) xs
                    f a ('1':xs) = f (2*a+1) xs
                in (f 0 vpart', rest)
             
demodulate :: String ->  (Block, String) 
demodulate ('0':'1':s) = let (v,r) = demodulate' s in (BNum v, r)
demodulate ('1':'0':s) = let (v,r) = demodulate' s in (BNum (-v), r)
demodulate ('0':'0':s) = (BNil, s)
demodulate ('1':'1':s) = let (v1,r1) = demodulate s
                             (v2,r2) = demodulate r1 

                         in (BPart "cons_2" [v1, v2], r2)
    
    

data PrettyState = ExBr| ExComma | ExNum deriving (Eq, Read, Show)
prettyDemodulate :: PrettyState -> String ->  String
prettyDemodulate _ "" = ""
prettyDemodulate ExNum ('0':'1':s) = let (v,r) = demodulate' s in show v ++ prettyDemodulate ExBr r
prettyDemodulate ExNum ('1':'0':s) = let (v,r) = demodulate' s in show (-v) ++ prettyDemodulate ExBr r
prettyDemodulate ExBr ('0':'1':s) = let (v,r) = demodulate' s in ", " ++ show v ++ prettyDemodulate ExBr r
prettyDemodulate ExBr ('1':'0':s) = let (v,r) = demodulate' s in ", " ++ show (-v) ++ prettyDemodulate ExBr r
prettyDemodulate ExNum ('0':'0':s) = "nil" ++ prettyDemodulate ExBr s
prettyDemodulate ExNum ('1':'1':s) = "(" ++ prettyDemodulate ExNum s
prettyDemodulate ExBr ('0':'0':s) = " )" ++ prettyDemodulate ExBr s
prettyDemodulate ExBr ('1':'1':s) = ", " ++ prettyDemodulate ExNum s

        
        
data Block = BNum Int | BName String | BApp Block Block | BPart String [Block] | BNil | BMod String | BList [Block] | BPicture [(Int,Int)] deriving (Eq, Read, Show)


readBlock :: [String] -> (Block, [String])
--readBlock [] = (NotApp, [])
readBlock ("nil":rest) = (BNil, rest)
readBlock ("ap":rest) = let (f, r1) = readBlock rest
                            (s, r2) = readBlock r1
                        in (BApp f s, r2)
readBlock (x:rest) | (isDigit $ head x )|| head x=='-' = (BNum (read x), rest)
                   | otherwise =  (BName x, rest)


evalBlock :: IntMap Block -> Block -> Block
evalBlock _ (BList []) = BNil
evalBlock im (BName n) = if head n == ':' then evalBlock im $ im IntMap.! (read$ traceShow n $tail n) else (BName n)
evalBlock im (BList (x:xs)) = evalBlock im $ BApp (BApp (BName "cons") x) (evalBlock im $ BList xs)
evalBlock im (BApp f arg) = let vf = evalBlock im f
                                BNum varg = evalBlock im arg
                                BMod vstr = evalBlock im arg
                                (BPart "cons_2" [pa,pb]) = evalBlock im arg
                                vblock = evalBlock im arg
                            in case vf of
                                (BName "add") ->  BPart "add_1" [ BNum varg]
                                (BPart "add_1" [BNum parg]) -> BNum (parg + varg)
                                (BName "inc") ->  BNum (varg + 1)
                                (BName "dec") ->  BNum (varg - 1)
                                (BName "mul") ->  BPart "mul_1" [ BNum varg]
                                (BPart "mul_1" [ BNum parg]) -> BNum (parg * varg)
                                (BName "div") ->  BPart "div_1" [ BNum varg]
                                (BPart "div_1" [ BNum parg]) -> BNum (parg `quot` varg)
                                (BName "eq") ->  BPart "eq_1" [ BNum varg]
                                (BPart "eq_1" [ BNum parg]) -> if varg == parg then BName "t" else BName "f"
                                (BName "lt") ->  BPart "lt_1" [ BNum varg]
                                (BPart "lt_1" [ BNum parg]) -> if parg < varg then BName "t" else BName "f"
                                (BName "mod") ->  case vblock of 
                                                       BNum varg  -> BMod $ modulate varg
                                                       BNil  -> BMod "00"
                                                       BPart "cons_2" [pa,pb] -> BMod $ "11" ++ (concat $ map  (\x -> let BMod res = evalBlock im $ BApp (BName "mod") x in res) [pa,pb]) 
                                                       BList xs -> BMod $  "11" ++ (concat $ intersperse "11" $ map (\x -> let BMod res = evalBlock im $ BApp (BName "mod") x in res) xs) ++ "00"
                                (BName "dem") ->  fst$demodulate vstr
                                (BName "send") ->  unsafePerformIO $ sendBlockToAliens $ evalBlock im $ BApp (BName"mod") vblock
                                (BName "neg") ->  BNum (- varg)
                                (BName "s") ->  BPart "s_1" [arg]
                                (BPart "s_1" [pa]) -> BPart "s_2" [pa, arg]
                                (BPart "s_2" [pa,pb]) -> BApp (BApp (evalBlock im pa) $ vblock) (BApp (evalBlock im pb) $vblock) 
                                (BName "c") ->  BPart "c_1" [arg]
                                (BPart "c_1" [pa]) -> BPart "c_2" [pa, arg]
                                (BPart "c_2" [pa,pb]) -> BApp (BApp (evalBlock im pa) (vblock))  (evalBlock im pb)
                                (BName "b") ->  BPart "b_1" [vblock]
                                (BPart "b_1" [pa]) -> BPart "b_2" [pa, vblock]
                                (BPart "b_2" [pa,pb]) -> BApp pa (BApp pb (vblock))
                                (BName "t") ->  BPart "t_1" [vblock]
                                (BPart "t_1" [pa]) -> pa
                                (BName "f") ->  BPart "f_1" []
                                (BPart "f_1" []) -> vblock
                                (BName "pwr2") ->  BNum (2 ^ varg )
                                (BName "i") ->  arg
                                (BName "cons") ->  BPart "cons_1" [vblock]
                                (BName "vec") ->  BPart "cons_1" [vblock]
                                (BPart "cons_1" [pa]) ->  BPart "cons_2" [pa,vblock]
                                (BPart "cons_2" [pa, pb]) ->  BApp(BApp vblock pa) pb
                                (BName "car") ->  pa
                                (BName "cdr") ->  pb
                                (BNil) -> BName "t"
                                (BName "isnil") ->  if vblock == BNil then BName "t" else BName "f" 
                                (BName "draw") -> case vblock of
                                                   BNil -> BPicture []
                                                   BPart "cons_2" [BPart "cons_2" [BNum x, BNum y],pb] -> let BPicture l = evalBlock im $ BApp (BName "draw") pb in BPicture $ (x,y):l
                                                   a -> error $ show a
                                (BName "multipledraw")  -> case vblock of
                                                               BNil -> BNil
                                                               BPart "cons_2" [p, r] -> let p1 = evalBlock im $ BApp (BName "draw") p
                                                                                            pr = evalBlock im $ BApp (BName "multipledraw") r
                                                                                        in BPart "cons_2" [p1, pr]
                                (BName "if0") ->  BPart "if0_1" [vblock]
                                (BPart "if0_1" [BNum pa]) -> if (pa == 0) then BPart "if0_20" [vblock] else BPart "if0_21" [] 
                                (BPart "if0_20" [pa]) -> pa
                                (BPart "if0_21" []) -> vblock
                                (BName "modem") -> BApp (BName "dem") $ BApp (BName "mod") vblock
                                (BName "f38") -> BPart "f38_1" [vblock]
                                (BPart "f38_1" [x2]) -> evalBlock im $BApp (BApp (BApp (BName "if0") (BApp (BName "car") vblock) )
                                 (BList[BApp (BName "modem") $ BApp (BName "car") $ BApp (BName "cdr") vblock , BApp (BName "multipledraw") $BApp (BName "car")$ BApp (BName "cdr")$ BApp (BName "cdr") vblock ]))
                                 (BApp (BApp (BApp (BName "interact") x2)  (BApp (BName "modem") $ BApp (BName "car") $ BApp (BName "cdr") vblock)) (BApp (BName "send") $ BApp (BName "car")$ BApp (BName "cdr")$ BApp (BName "cdr") vblock))
                                (BName "interact") -> BPart "interact_1" [vblock]
                                (BPart "interact_1" [pa]) -> BPart "interact_2" [pa, vblock]
                                (BPart "interact_2" [x2, x4]) ->  evalBlock im $BApp (BApp (BName "f38") x2) (BApp (BApp x2 x4) vblock)
                                (BName "statelessdraw") -> BPart "statelessdraw_1" [vblock]
                                (BPart "statelessdraw_1" [x0]) -> BList [BNum 0, BNil, BList [BList [vblock]]]
                                (BName "stateful1") -> BPart "stateful1_1" [vblock]
                                (BPart "stateful1_1" [x0]) -> BList [BNum 0, BPart "cons_2" [vblock, x0], BList [BPart "cons_2" [vblock, x0]]] --( 0 , ap ap cons x1 x0 , ( ap ap cons x1 x0 ) )
                                b -> error $ show b
                             

evalBlock _ b = b

evalBlock' = evalBlock IntMap.empty

{-
evalAll :: Block -> Block
evalAll b1 = let b2 = evalBlock b1
             in if b1 == b2 then b2
                else evalAll b2
-}
sendBlockToAliens :: Block -> IO Block
sendBlockToAliens (BMod x) = 
    do res <- sendtoAliens x
       return $ fst$demodulate res

sendtoAliens msg = do
    request' <- parseRequest ("POST " ++ "https://icfpc2020-api.testkontur.ru/aliens/send?apiKey=b4c1d7d8042e46c7a5e59574839f41b9")
    putStrLn $ "Sending message: " ++ msg
    let request = setRequestBodyLBS (BLU.fromString msg) request'
    response <- httpLBS request
    let statuscode = show (getResponseStatusCode response)
        strResp = BLU.toString (getResponseBody response)
    case statuscode of
        "200" -> putStrLn ("Server response: " ++ strResp)
        _ -> putStrLn ("Unexpected server response:\nHTTP code: " ++ statuscode ++ "\nResponse body: " ++ strResp)
    return strResp
    
readGalaxy :: IO  Block
readGalaxy = 
    do  f <- readFile "galaxy.txt"
        let ls = lines f
            im = foldl (\m l -> let (n:_:bs) =  words l 
                                in IntMap.insert (read $ tail n) (fst $ readBlock bs) m) IntMap.empty  $ take 392 ls
        return $ evalBlock im $ BApp (BApp ( BApp (BName "interact") (im IntMap.! 1338)) BNil) (BApp (BApp (BName "cons") (BNum 0)) (BNum 0))
        

sendJoinRequest = sendBlockToAliens $ evalBlock' $  BApp (BName "mod") $ BList [BNum 2, BNum 1440052318050416603, BNil]


