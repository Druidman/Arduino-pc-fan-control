function switchColorIPC(){
    window.electronAPI.switchColor()    
}
function shutdownIPC(){
    window.electronAPI.shutdown()    
}

export {
    switchColorIPC,
    shutdownIPC
}