
"use strict";

let GetCoords = require('./GetCoords.js')
let PumpStatus = require('./PumpStatus.js')
let SetEndType = require('./SetEndType.js')
let SetAngles = require('./SetAngles.js')
let SetCoords = require('./SetCoords.js')
let GetAngles = require('./GetAngles.js')
let GripperStatus = require('./GripperStatus.js')
let SetFreshMode = require('./SetFreshMode.js')
let SetToolReference = require('./SetToolReference.js')

module.exports = {
  GetCoords: GetCoords,
  PumpStatus: PumpStatus,
  SetEndType: SetEndType,
  SetAngles: SetAngles,
  SetCoords: SetCoords,
  GetAngles: GetAngles,
  GripperStatus: GripperStatus,
  SetFreshMode: SetFreshMode,
  SetToolReference: SetToolReference,
};
