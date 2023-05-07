const { spawn } = require('child_process');

function childProcessPromise(command, args) {
  return new Promise((resolve, reject) => {
    const childProcess = spawn(command, args);
    childProcess.stdout.on('data', (data) => {
      console.log(`${command}: stdout: ${data}`);
    });
    childProcess.stderr.on('data', (data) => {
      console.error(`${command}: stderr: ${data}`);
    });
    childProcess.on('close', (code) => {
      console.log(`${command} child process exited with code ${code}`);
      resolve();
    });
  });
}

async function runChildProcesses() {
  await childProcessPromise('./fileOpen', ['none']);
  await childProcessPromise('./position', ['none']);
  await childProcessPromise('./writeAndRead', ['none']);
}

runChildProcesses().catch((err) => {
  console.error(err);
});