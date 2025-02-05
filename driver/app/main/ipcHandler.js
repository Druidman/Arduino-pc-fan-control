const { ipcMain } = require("electron")
const { createPortConnection } = require("./serialPortCom.js")

function setupIpcHandler(){
    const port = createPortConnection()

    if (!port){
        return false
    }
    ipcMain.on("switchColor",(Event)=>{
        port.write("CLICK/")
        Event.returnValue = true
    })
    ipcMain.on("shutdown",(Event)=>{
        port.write("HOLD/")
        Event.returnValue = true
    })
    return true
}

module.exports = { setupIpcHandler }