



const { SerialPort } = require("serialport")




async function createPortConnection(){
    const portName ="/dev/ttyUSB0"
    const baudRate = 9600

    
    const port = new SerialPort({
        path: portName, 
        baudRate: baudRate
      });
    
    if (!port){
        console.log("NOT PORT")
        return null
    }


    const delay = new Promise(resolve => setTimeout(resolve,3000))
    await delay

    writeToPort(port,{
        "AIO_RGB": {"r":"0","g":"150","b":"100"}
    })
    // writeToPort(port,{
    //     "CASE_FAN_LED_MODE": "20"
    // })
    console.log("config sent")
    
    
    return port

}
function writeToPort(port,data){
    data = JSON.stringify(data) + "/"
    console.log(`SEnding ${data}`)
    port.write(data)

    


    
}
module.exports = {
    createPortConnection,
    writeToPort
}