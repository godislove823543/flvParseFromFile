# flvParseFromFile

1. FlvResolver（被註解掉）主要是解析 FLV container 結構：

header

tag header + tag size

不解析 tag data

2. parseScriptData 則是 解析 tag 內的資料（metadata/script）

3. 流程:

建立 FlvResolver 物件
        ↓
openFile(path)
        ↓
resolveFlvHeader()
        ↓
printHeader()
        ↓
resolveFlvBody()
    ├─ 先讀 PreviousTagSize0
    ├─ 再讀 Tag1
    ├─ 根據 DataSize 跳過資料內容
    ├─ 印出 Tag1 資訊
    ├─ 讀下一個 PreviousTagSize
    ├─ 讀下一個 Tag
    └─ 重複直到檔案結尾
        ↓
解構時自動 fclose(file)

