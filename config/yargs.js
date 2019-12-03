const argv = require('yargs').options({
    ip: {
        default: '192.168.0.100',
        alias: 'i',
        desc: 'ip del broker'
    }
}).argv;

module.exports = {
    argv
};