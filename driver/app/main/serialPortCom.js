const { SerialPort } = require("serialport")


function createPortConnection(){
    const portName ="/dev/ttyUSB0"
    const baudRate = 9600

    const port = new SerialPort(
        {
            path: portName,
            baudRate: baudRate
        }
    )

    if (!port){
        
        return null
    }

    return port

}

module.exports = {
    createPortConnection
}