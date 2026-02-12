; Auto-generated. Do not edit!


(cl:in-package mycobot_communication-srv)


;//! \htmlinclude SetFreshMode-request.msg.html

(cl:defclass <SetFreshMode-request> (roslisp-msg-protocol:ros-message)
  ((Status
    :reader Status
    :initarg :Status
    :type cl:fixnum
    :initform 0))
)

(cl:defclass SetFreshMode-request (<SetFreshMode-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetFreshMode-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetFreshMode-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mycobot_communication-srv:<SetFreshMode-request> is deprecated: use mycobot_communication-srv:SetFreshMode-request instead.")))

(cl:ensure-generic-function 'Status-val :lambda-list '(m))
(cl:defmethod Status-val ((m <SetFreshMode-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mycobot_communication-srv:Status-val is deprecated.  Use mycobot_communication-srv:Status instead.")
  (Status m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetFreshMode-request>) ostream)
  "Serializes a message object of type '<SetFreshMode-request>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Status)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetFreshMode-request>) istream)
  "Deserializes a message object of type '<SetFreshMode-request>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Status)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetFreshMode-request>)))
  "Returns string type for a service object of type '<SetFreshMode-request>"
  "mycobot_communication/SetFreshModeRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetFreshMode-request)))
  "Returns string type for a service object of type 'SetFreshMode-request"
  "mycobot_communication/SetFreshModeRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetFreshMode-request>)))
  "Returns md5sum for a message object of type '<SetFreshMode-request>"
  "9dfdf50aef7688b8c7d43efb64190a81")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetFreshMode-request)))
  "Returns md5sum for a message object of type 'SetFreshMode-request"
  "9dfdf50aef7688b8c7d43efb64190a81")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetFreshMode-request>)))
  "Returns full string definition for message of type '<SetFreshMode-request>"
  (cl:format cl:nil "uint8 Status~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetFreshMode-request)))
  "Returns full string definition for message of type 'SetFreshMode-request"
  (cl:format cl:nil "uint8 Status~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetFreshMode-request>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetFreshMode-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SetFreshMode-request
    (cl:cons ':Status (Status msg))
))
;//! \htmlinclude SetFreshMode-response.msg.html

(cl:defclass <SetFreshMode-response> (roslisp-msg-protocol:ros-message)
  ((Flag
    :reader Flag
    :initarg :Flag
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass SetFreshMode-response (<SetFreshMode-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetFreshMode-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetFreshMode-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mycobot_communication-srv:<SetFreshMode-response> is deprecated: use mycobot_communication-srv:SetFreshMode-response instead.")))

(cl:ensure-generic-function 'Flag-val :lambda-list '(m))
(cl:defmethod Flag-val ((m <SetFreshMode-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mycobot_communication-srv:Flag-val is deprecated.  Use mycobot_communication-srv:Flag instead.")
  (Flag m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetFreshMode-response>) ostream)
  "Serializes a message object of type '<SetFreshMode-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'Flag) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetFreshMode-response>) istream)
  "Deserializes a message object of type '<SetFreshMode-response>"
    (cl:setf (cl:slot-value msg 'Flag) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetFreshMode-response>)))
  "Returns string type for a service object of type '<SetFreshMode-response>"
  "mycobot_communication/SetFreshModeResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetFreshMode-response)))
  "Returns string type for a service object of type 'SetFreshMode-response"
  "mycobot_communication/SetFreshModeResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetFreshMode-response>)))
  "Returns md5sum for a message object of type '<SetFreshMode-response>"
  "9dfdf50aef7688b8c7d43efb64190a81")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetFreshMode-response)))
  "Returns md5sum for a message object of type 'SetFreshMode-response"
  "9dfdf50aef7688b8c7d43efb64190a81")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetFreshMode-response>)))
  "Returns full string definition for message of type '<SetFreshMode-response>"
  (cl:format cl:nil "~%bool Flag~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetFreshMode-response)))
  "Returns full string definition for message of type 'SetFreshMode-response"
  (cl:format cl:nil "~%bool Flag~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetFreshMode-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetFreshMode-response>))
  "Converts a ROS message object to a list"
  (cl:list 'SetFreshMode-response
    (cl:cons ':Flag (Flag msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'SetFreshMode)))
  'SetFreshMode-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'SetFreshMode)))
  'SetFreshMode-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetFreshMode)))
  "Returns string type for a service object of type '<SetFreshMode>"
  "mycobot_communication/SetFreshMode")