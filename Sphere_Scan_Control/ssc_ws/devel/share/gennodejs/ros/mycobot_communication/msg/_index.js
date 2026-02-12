
"use strict";

let MycobotSetAngles = require('./MycobotSetAngles.js');
let MycobotAngles = require('./MycobotAngles.js');
let MycobotSetFreshMode = require('./MycobotSetFreshMode.js');
let MycobotCoords = require('./MycobotCoords.js');
let MycobotPumpStatus = require('./MycobotPumpStatus.js');
let MycobotSetEndType = require('./MycobotSetEndType.js');
let MycobotSetCoords = require('./MycobotSetCoords.js');
let MycobotGripperStatus = require('./MycobotGripperStatus.js');
let MycobotSetToolReference = require('./MycobotSetToolReference.js');

module.exports = {
  MycobotSetAngles: MycobotSetAngles,
  MycobotAngles: MycobotAngles,
  MycobotSetFreshMode: MycobotSetFreshMode,
  MycobotCoords: MycobotCoords,
  MycobotPumpStatus: MycobotPumpStatus,
  MycobotSetEndType: MycobotSetEndType,
  MycobotSetCoords: MycobotSetCoords,
  MycobotGripperStatus: MycobotGripperStatus,
  MycobotSetToolReference: MycobotSetToolReference,
};
