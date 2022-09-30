# frozen_string_literal: true

require_relative "framegrabber/version"
require "grab_frame_ext"
begin
  require 'rmagick'
rescue LoadError
end


module Framegrabber
  if const_defined?("Magick")
    def self.grab_image
      frame = grab_frame
      Magick::Image.constitute(frame.first.size, frame.size, "BGR", frame.flatten)
    end
  end
end
