const { ipcMain } = require("electron")
const { SerialPort }  = require("serialport")


function setupIpcHandler(){
    const port = new SerialPort({path: "/dev/ttyUSB0",baudRate: 9600})
    ipcMain.on("switchColor",(Event)=>{
        port.write("CLICK/")
        Event.returnValue = true
    })
    ipcMain.on("shutdown",(Event)=>{
        port.write("HOLD/")
        Event.returnValue = true
    })
}

module.exports = { setupIpcHandler }