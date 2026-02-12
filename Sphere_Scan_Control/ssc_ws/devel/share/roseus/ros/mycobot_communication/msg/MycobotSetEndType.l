;; Auto-generated. Do not edit!


(when (boundp 'mycobot_communication::MycobotSetEndType)
  (if (not (find-package "MYCOBOT_COMMUNICATION"))
    (make-package "MYCOBOT_COMMUNICATION"))
  (shadow 'MycobotSetEndType (find-package "MYCOBOT_COMMUNICATION")))
(unless (find-package "MYCOBOT_COMMUNICATION::MYCOBOTSETENDTYPE")
  (make-package "MYCOBOT_COMMUNICATION::MYCOBOTSETENDTYPE"))

(in-package "ROS")
;;//! \htmlinclude MycobotSetEndType.msg.html


(defclass mycobot_communication::MycobotSetEndType
  :super ros::object
  :slots (_Status ))

(defmethod mycobot_communication::MycobotSetEndType
  (:init
   (&key
    ((:Status __Status) 0)
    )
   (send-super :init)
   (setq _Status (round __Status))
   self)
  (:Status
   (&optional __Status)
   (if __Status (setq _Status __Status)) _Status)
  (:serialization-length
   ()
   (+
    ;; uint8 _Status
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _Status
       (write-byte _Status s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _Status
     (setq _Status (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get mycobot_communication::MycobotSetEndType :md5sum-) "5fa862b628cefe7464ed489433f1bba8")
(setf (get mycobot_communication::MycobotSetEndType :datatype-) "mycobot_communication/MycobotSetEndType")
(setf (get mycobot_communication::MycobotSetEndType :definition-)
      "uint8 Status
")



(provide :mycobot_communication/MycobotSetEndType "5fa862b628cefe7464ed489433f1bba8")


