# flvParseFromFile

解析FLV串流檔案格式

流程:

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

