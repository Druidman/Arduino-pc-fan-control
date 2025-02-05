import { regulateSpeed , switchColorIPC, shutdownIPC } from "./ipcHandler.js";

document.getElementById("switchColor").addEventListener("click",(event)=>{
    switchColorIPC()
})

document.getElementById("shutdown").addEventListener("click",(event)=>{
    shutdownIPC()
})

document.getElementById("speedSlider").addEventListener("input",(event)=>{
    let speed = event.currentTarget.value
    regulateSpeed(speed)
})