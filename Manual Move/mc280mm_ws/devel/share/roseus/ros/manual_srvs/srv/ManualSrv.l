;; Auto-generated. Do not edit!


(when (boundp 'manual_srvs::ManualSrv)
  (if (not (find-package "MANUAL_SRVS"))
    (make-package "MANUAL_SRVS"))
  (shadow 'ManualSrv (find-package "MANUAL_SRVS")))
(unless (find-package "MANUAL_SRVS::MANUALSRV")
  (make-package "MANUAL_SRVS::MANUALSRV"))
(unless (find-package "MANUAL_SRVS::MANUALSRVREQUEST")
  (make-package "MANUAL_SRVS::MANUALSRVREQUEST"))
(unless (find-package "MANUAL_SRVS::MANUALSRVRESPONSE")
  (make-package "MANUAL_SRVS::MANUALSRVRESPONSE"))

(in-package "ROS")





(defclass manual_srvs::ManualSrvRequest
  :super ros::object
  :slots (_angles ))

(defmethod manual_srvs::ManualSrvRequest
  (:init
   (&key
    ((:angles __angles) (make-array 6 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _angles __angles)
   self)
  (:angles
   (&optional __angles)
   (if __angles (setq _angles __angles)) _angles)
  (:serialization-length
   ()
   (+
    ;; float64[6] _angles
    (* 8    6)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64[6] _angles
     (dotimes (i 6)
       (sys::poke (elt _angles i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64[6] _angles
   (dotimes (i (length _angles))
     (setf (elt _angles i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;;
   self)
  )

(defclass manual_srvs::ManualSrvResponse
  :super ros::object
  :slots (_success ))

(defmethod manual_srvs::ManualSrvResponse
  (:init
   (&key
    ((:success __success) nil)
    )
   (send-super :init)
   (setq _success __success)
   self)
  (:success
   (&optional (__success :null))
   (if (not (eq __success :null)) (setq _success __success)) _success)
  (:serialization-length
   ()
   (+
    ;; bool _success
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _success
       (if _success (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _success
     (setq _success (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass manual_srvs::ManualSrv
  :super ros::object
  :slots ())

(setf (get manual_srvs::ManualSrv :md5sum-) "cb9460bf78e499f0b8513944c7615a57")
(setf (get manual_srvs::ManualSrv :datatype-) "manual_srvs/ManualSrv")
(setf (get manual_srvs::ManualSrv :request) manual_srvs::ManualSrvRequest)
(setf (get manual_srvs::ManualSrv :response) manual_srvs::ManualSrvResponse)

(defmethod manual_srvs::ManualSrvRequest
  (:response () (instance manual_srvs::ManualSrvResponse :init)))

(setf (get manual_srvs::ManualSrvRequest :md5sum-) "cb9460bf78e499f0b8513944c7615a57")
(setf (get manual_srvs::ManualSrvRequest :datatype-) "manual_srvs/ManualSrvRequest")
(setf (get manual_srvs::ManualSrvRequest :definition-)
      "float64[6] angles
---
bool success

")

(setf (get manual_srvs::ManualSrvResponse :md5sum-) "cb9460bf78e499f0b8513944c7615a57")
(setf (get manual_srvs::ManualSrvResponse :datatype-) "manual_srvs/ManualSrvResponse")
(setf (get manual_srvs::ManualSrvResponse :definition-)
      "float64[6] angles
---
bool success

")



(provide :manual_srvs/ManualSrv "cb9460bf78e499f0b8513944c7615a57")


