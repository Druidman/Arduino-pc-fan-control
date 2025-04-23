const { ipcMain } = require("electron")
const { createPortConnection, writeToPort } = require("./serialPortCom.js")


function setupIpcHandler(){
    const port = createPortConnection()

    if (!port){
        return false
    }
    ipcMain.on("switchColor",(Event)=>{
        writeToPort(port,{"CLICK": 1})
        Event.returnValue = true
    })
    ipcMain.on("shutdown",(Event)=>{
        writeToPort(port,{"HOLD": 1})
        Event.returnValue = true
    })
    ipcMain.on("speedRegulation",(Event,speed)=>{
        data = {
            "SPEED": speed
        }
        writeToPort(port,data)
        Event.returnValue = true
    })
    ipcMain.on("switchLedMode",(Event,mode)=>{
        data = {
            "LED_MODE": mode
        }
        writeToPort(port,data)
        Event.returnValue = true
    })
    return true
}

module.exports = { setupIpcHandler }