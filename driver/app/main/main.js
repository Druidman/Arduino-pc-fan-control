const { app, BrowserWindow} = require('electron')
const path = require("path")

const createWindow = () => {
  const win = new BrowserWindow({
    width: 800,
    height: 600
  })

  let path_to_file = path.join(__dirname,"../renderer/mainWindow/pages/index.html")

  win.loadFile(path_to_file)
}

app.whenReady().then(() => {
  createWindow()
})