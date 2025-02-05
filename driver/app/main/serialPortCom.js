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
function writeToPort(port,data){
    port.write(JSON.stringify(data) + "/")
}
module.exports = {
    createPortConnection,
    writeToPort
}