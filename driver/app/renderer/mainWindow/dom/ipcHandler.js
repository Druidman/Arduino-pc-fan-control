function switchColorIPC(){
    window.electronAPI.switchCaseFanColor()    
}
function shutdownIPC(){
    window.electronAPI.shutdown()    
}
function regulateSpeed(speed){
    window.electronAPI.regulateSpeed(speed)
}
function switchLedModeIPC(mode){
    window.electronAPI.switchCaseFanLedMode(mode)
}
function changeAioColor(r,g,b){
    window.electronAPI.changeAioColor(r,g,b)
}
export {
    switchColorIPC,
    shutdownIPC,
    regulateSpeed,
    switchLedModeIPC,
    changeAioColor
}