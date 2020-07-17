import System.Environment
import Network.HTTP.Simple
import Data.ByteString.Lazy.UTF8 as BLU
import Control.Exception


send url msg = do
    request' <- parseRequest ("POST " ++ url)
    putStrLn $ "Sending message: " ++ msg
    let request = setRequestBodyLBS (BLU.fromString msg) request'
    response <- httpLBS request
    let statuscode = show (getResponseStatusCode response)
        strResp = BLU.toString (getResponseBody response)
    case statuscode of
        "200" -> putStrLn ("Server response: " ++ strResp)
        _ -> putStrLn ("Unexpected server response:\nHTTP code: " ++ statuscode ++ "\nResponse body: " ++ strResp)
    return strResp

main = catch (
    do  
        args <- getArgs
        putStrLn ("ServerUrl: " ++ args!!0 ++ "; PlayerKey: " ++ args!!1)
        
        r <- send (args!!0) (args!!1)
        r <- send (args!!0) "1101000"
        return ()

    ) handler
    where
        handler :: SomeException -> IO ()
        handler ex = putStrLn $ "Unexpected server response:\n" ++ show ex
