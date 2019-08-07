#!/usr/bin/env ruby
require 'ffi-rzmq'

# CLI arguments
sp = (ARGV[0] || 0).to_f    # set point
n  = (ARGV[1] || 10).to_i   # number of points to get
dt = (ARGV[2] || 0.01).to_f # sampling time

# Socket to talk to server
context = ZMQ::Context.new(1)
requester = context.socket(ZMQ::REQ)
requester.connect("tcp://bbpb.local:5555")

reply = ''
puts "i, ts, t, x, y, z, xdot, ydot, zdot"
requester.send_string "s#{sp}"
n.times do |i|
  requester.send_string "."
  rc = requester.recv_string(reply)
  puts "#{i}, #{reply}"
  sleep dt
end

# Uncomment to request stop at the end (not really necessary)
# requester.send_string "X"
