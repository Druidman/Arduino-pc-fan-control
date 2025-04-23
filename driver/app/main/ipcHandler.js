const { ipcMain } = require("electron")
const { createPortConnection, writeToPort } = require("./serialPortCom.js")


async function setupIpcHandler(){
    const port = await createPortConnection()

    if (!port){
        return false
    }
    ipcMain.on("switchCaseFanColor",(Event)=>{
        writeToPort(port,{"CLICK": 1})
        Event.returnValue = true
    })
    ipcMain.on("shutdown",(Event)=>{
        writeToPort(port,{
            "HOLD": 1
        })
        Event.returnValue = true
    })
    ipcMain.on("speedRegulation",(Event,speed)=>{
        data = {
            "SPEED": speed
        }
        writeToPort(port,data)
        Event.returnValue = true
    })
    ipcMain.on("switchCaseFanLedMode",(Event,mode)=>{
        data = {
            "CASE_FAN_LED_MODE": mode
        }
        writeToPort(port,data)
        Event.returnValue = true
    })
    ipcMain.on("changeAioColor",(Event,r,g,b)=>{
        data = {
            "AIO_RGB": {"r":r,"g":g,"b":b}
        }
        writeToPort(port,data)
        Event.returnValue = true
    })
    return true
}

module.exports = { setupIpcHandler }