; Auto-generated. Do not edit!


(cl:in-package manual_srvs-srv)


;//! \htmlinclude SetJointAngles-request.msg.html

(cl:defclass <SetJointAngles-request> (roslisp-msg-protocol:ros-message)
  ((angles
    :reader angles
    :initarg :angles
    :type (cl:vector cl:float)
   :initform (cl:make-array 6 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass SetJointAngles-request (<SetJointAngles-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetJointAngles-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetJointAngles-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name manual_srvs-srv:<SetJointAngles-request> is deprecated: use manual_srvs-srv:SetJointAngles-request instead.")))

(cl:ensure-generic-function 'angles-val :lambda-list '(m))
(cl:defmethod angles-val ((m <SetJointAngles-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader manual_srvs-srv:angles-val is deprecated.  Use manual_srvs-srv:angles instead.")
  (angles m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetJointAngles-request>) ostream)
  "Serializes a message object of type '<SetJointAngles-request>"
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-double-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream)))
   (cl:slot-value msg 'angles))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetJointAngles-request>) istream)
  "Deserializes a message object of type '<SetJointAngles-request>"
  (cl:setf (cl:slot-value msg 'angles) (cl:make-array 6))
  (cl:let ((vals (cl:slot-value msg 'angles)))
    (cl:dotimes (i 6)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-double-float-bits bits)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetJointAngles-request>)))
  "Returns string type for a service object of type '<SetJointAngles-request>"
  "manual_srvs/SetJointAnglesRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetJointAngles-request)))
  "Returns string type for a service object of type 'SetJointAngles-request"
  "manual_srvs/SetJointAnglesRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetJointAngles-request>)))
  "Returns md5sum for a message object of type '<SetJointAngles-request>"
  "cb9460bf78e499f0b8513944c7615a57")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetJointAngles-request)))
  "Returns md5sum for a message object of type 'SetJointAngles-request"
  "cb9460bf78e499f0b8513944c7615a57")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetJointAngles-request>)))
  "Returns full string definition for message of type '<SetJointAngles-request>"
  (cl:format cl:nil "float64[6] angles~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetJointAngles-request)))
  "Returns full string definition for message of type 'SetJointAngles-request"
  (cl:format cl:nil "float64[6] angles~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetJointAngles-request>))
  (cl:+ 0
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'angles) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetJointAngles-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SetJointAngles-request
    (cl:cons ':angles (angles msg))
))
;//! \htmlinclude SetJointAngles-response.msg.html

(cl:defclass <SetJointAngles-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass SetJointAngles-response (<SetJointAngles-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetJointAngles-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetJointAngles-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name manual_srvs-srv:<SetJointAngles-response> is deprecated: use manual_srvs-srv:SetJointAngles-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <SetJointAngles-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader manual_srvs-srv:success-val is deprecated.  Use manual_srvs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetJointAngles-response>) ostream)
  "Serializes a message object of type '<SetJointAngles-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetJointAngles-response>) istream)
  "Deserializes a message object of type '<SetJointAngles-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetJointAngles-response>)))
  "Returns string type for a service object of type '<SetJointAngles-response>"
  "manual_srvs/SetJointAnglesResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetJointAngles-response)))
  "Returns string type for a service object of type 'SetJointAngles-response"
  "manual_srvs/SetJointAnglesResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetJointAngles-response>)))
  "Returns md5sum for a message object of type '<SetJointAngles-response>"
  "cb9460bf78e499f0b8513944c7615a57")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetJointAngles-response)))
  "Returns md5sum for a message object of type 'SetJointAngles-response"
  "cb9460bf78e499f0b8513944c7615a57")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetJointAngles-response>)))
  "Returns full string definition for message of type '<SetJointAngles-response>"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetJointAngles-response)))
  "Returns full string definition for message of type 'SetJointAngles-response"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetJointAngles-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetJointAngles-response>))
  "Converts a ROS message object to a list"
  (cl:list 'SetJointAngles-response
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'SetJointAngles)))
  'SetJointAngles-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'SetJointAngles)))
  'SetJointAngles-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetJointAngles)))
  "Returns string type for a service object of type '<SetJointAngles>"
  "manual_srvs/SetJointAngles")