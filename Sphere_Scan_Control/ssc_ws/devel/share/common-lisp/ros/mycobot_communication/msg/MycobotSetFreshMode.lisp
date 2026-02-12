; Auto-generated. Do not edit!


(cl:in-package mycobot_communication-msg)


;//! \htmlinclude MycobotSetFreshMode.msg.html

(cl:defclass <MycobotSetFreshMode> (roslisp-msg-protocol:ros-message)
  ((Status
    :reader Status
    :initarg :Status
    :type cl:fixnum
    :initform 0))
)

(cl:defclass MycobotSetFreshMode (<MycobotSetFreshMode>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <MycobotSetFreshMode>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'MycobotSetFreshMode)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mycobot_communication-msg:<MycobotSetFreshMode> is deprecated: use mycobot_communication-msg:MycobotSetFreshMode instead.")))

(cl:ensure-generic-function 'Status-val :lambda-list '(m))
(cl:defmethod Status-val ((m <MycobotSetFreshMode>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mycobot_communication-msg:Status-val is deprecated.  Use mycobot_communication-msg:Status instead.")
  (Status m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <MycobotSetFreshMode>) ostream)
  "Serializes a message object of type '<MycobotSetFreshMode>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Status)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <MycobotSetFreshMode>) istream)
  "Deserializes a message object of type '<MycobotSetFreshMode>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Status)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<MycobotSetFreshMode>)))
  "Returns string type for a message object of type '<MycobotSetFreshMode>"
  "mycobot_communication/MycobotSetFreshMode")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'MycobotSetFreshMode)))
  "Returns string type for a message object of type 'MycobotSetFreshMode"
  "mycobot_communication/MycobotSetFreshMode")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<MycobotSetFreshMode>)))
  "Returns md5sum for a message object of type '<MycobotSetFreshMode>"
  "5fa862b628cefe7464ed489433f1bba8")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'MycobotSetFreshMode)))
  "Returns md5sum for a message object of type 'MycobotSetFreshMode"
  "5fa862b628cefe7464ed489433f1bba8")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<MycobotSetFreshMode>)))
  "Returns full string definition for message of type '<MycobotSetFreshMode>"
  (cl:format cl:nil "uint8 Status~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'MycobotSetFreshMode)))
  "Returns full string definition for message of type 'MycobotSetFreshMode"
  (cl:format cl:nil "uint8 Status~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <MycobotSetFreshMode>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <MycobotSetFreshMode>))
  "Converts a ROS message object to a list"
  (cl:list 'MycobotSetFreshMode
    (cl:cons ':Status (Status msg))
))
