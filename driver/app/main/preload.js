const { contextBridge, ipcRenderer } = require("electron")







contextBridge.exposeInMainWorld("electronAPI", {
    switchCaseFanColor: ()=> ipcRenderer.sendSync("switchCaseFanColor"),
    shutdown: ()=> ipcRenderer.sendSync("shutdown"),
    regulateSpeed: (speed)=>ipcRenderer.sendSync("speedRegulation",speed),
    switchCaseFanLedMode: (mode)=>ipcRenderer.sendSync("switchCaseFanLedMode",mode),
    changeAioColor: (r,g,b)=>ipcRenderer.sendSync("changeAioColor",r,g,b)
    
})