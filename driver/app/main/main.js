const { app, BrowserWindow} = require('electron')
const path = require("path")
const { setupIpcHandler }  = require("./ipcHandler.js")

const createWindow = async () => {
  const win = new BrowserWindow({
    width: 1280,
    height: 720,
    webPreferences: {
        preload: path.join(__dirname, 'preload.js')
    }
  })
  if (!await setupIpcHandler()){
    app.quit()
  }
  let path_to_file = path.join(__dirname,"../renderer/mainWindow/pages/index.html")

  win.loadFile(path_to_file)
 
  
}

app.whenReady().then(async () => {
  await createWindow()


  
})