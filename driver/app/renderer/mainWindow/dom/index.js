import { regulateSpeed , switchColorIPC, shutdownIPC, switchLedModeIPC, changeAioColor } from "./ipcHandler.js";

document.getElementById("switchCaseFanColor").addEventListener("click",(event)=>{
    switchColorIPC()
})

document.getElementById("shutdown").addEventListener("click",(event)=>{
    shutdownIPC()
})

document.getElementById("speedSlider").addEventListener("input",(event)=>{
    let speed = event.currentTarget.value
    regulateSpeed(speed)
})

document.getElementById("submitCaseFanMode").addEventListener("click",(event)=>{
    
    let mode = document.getElementById("CaseFanMode").value
    
    switchLedModeIPC(mode)

})

document.getElementById("submitAIO").addEventListener("click",(event)=>{
    let picker = document.getElementById("aioColor")
    let color = picker.value
    let colorRGB = hexToRgb(color)
    
    changeAioColor(colorRGB.r,colorRGB.g,colorRGB.b)

})
function hexToRgb(hex) {
    var result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex);
    return result ? {
      r: parseInt(result[1], 16),
      g: parseInt(result[2], 16),
      b: parseInt(result[3], 16)
    } : null;
  }
  