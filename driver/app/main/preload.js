const { contextBridge, ipcRenderer } = require("electron")







contextBridge.exposeInMainWorld("electronAPI", {
    switchColor: ()=> ipcRenderer.sendSync("switchColor"),
    shutdown: ()=> ipcRenderer.sendSync("shutdown"),
    regulateSpeed: (speed)=>ipcRenderer.sendSync("speedRegulation",speed),
    switchLedMode: (mode)=>ipcRenderer.sendSync("switchLedMode",mode)
    
    
})