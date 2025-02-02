const { contextBridge, ipcRenderer } = require("electron")






contextBridge.exposeInMainWorld("electronAPI", {
    switchColor: ()=> ipcRenderer.sendSync("switchColor"),
    shutdown: ()=> ipcRenderer.sendSync("shutdown")
    
})