import { regulateSpeed , switchColorIPC, shutdownIPC, switchLedModeIPC } from "./ipcHandler.js";

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

document.getElementById("fanMode").addEventListener("input",(event)=>{
    console.log("calue")
    let mode = event.currentTarget.value
    console.log(mode)
    switchLedModeIPC(mode)

})