const { app, BrowserWindow} = require('electron')
const path = require("path")
const { setupIpcHandler }  = require("./ipcHandler.js")

const createWindow = () => {
  const win = new BrowserWindow({
    width: 800,
    height: 600,
    webPreferences: {
        preload: path.join(__dirname, 'preload.js')
    }
  })
  setupIpcHandler()
  let path_to_file = path.join(__dirname,"../renderer/mainWindow/pages/index.html")

  win.loadFile(path_to_file)
  
}

app.whenReady().then(() => {
  createWindow()
})