# flvParseFromFile

1. FlvResolver（被註解掉）主要是解析 FLV container 結構：

header

tag header + tag size

不解析 tag data

2. parseScriptData 則是 解析 tag 內的資料（metadata/script）

