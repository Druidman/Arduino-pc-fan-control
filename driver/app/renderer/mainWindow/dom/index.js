import { switchColorIPC, shutdownIPC } from "./ipcHandler.js";

document.getElementById("switchColor").addEventListener("click",(event)=>{
    switchColorIPC()
})

document.getElementById("shutdown").addEventListener("click",(event)=>{
    shutdownIPC()
})