function switchColorIPC(){
    window.electronAPI.switchColor()    
}
function shutdownIPC(){
    window.electronAPI.shutdown()    
}
function regulateSpeed(speed){
    window.electronAPI.regulateSpeed(speed)
}

export {
    switchColorIPC,
    shutdownIPC,
    regulateSpeed
}