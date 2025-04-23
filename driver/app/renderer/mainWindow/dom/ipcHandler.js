function switchColorIPC(){
    window.electronAPI.switchColor()    
}
function shutdownIPC(){
    window.electronAPI.shutdown()    
}
function regulateSpeed(speed){
    window.electronAPI.regulateSpeed(speed)
}
function switchLedModeIPC(mode){
    window.electronAPI.switchLedMode(mode)
}
export {
    switchColorIPC,
    shutdownIPC,
    regulateSpeed,
    switchLedModeIPC
}