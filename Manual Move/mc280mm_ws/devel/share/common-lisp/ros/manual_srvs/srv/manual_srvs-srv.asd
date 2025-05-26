
(cl:in-package :asdf)

(defsystem "manual_srvs-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "SetJointAngles" :depends-on ("_package_SetJointAngles"))
    (:file "_package_SetJointAngles" :depends-on ("_package"))
  ))