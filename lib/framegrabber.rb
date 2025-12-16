# frozen_string_literal: true

require_relative 'framegrabber/version'
require 'grab_frame_ext'
begin
  require 'rmagick'
rescue LoadError
end

module Framegrabber
  if const_defined?('Magick')
    def self.grab_image
      frame = grab_frame
      # Scale 8-bit values (0-255) to 16-bit quantum range (0-65535)
      scaled_pixels = frame.flatten.map { |v| (v * 257).to_i } # 257 = 65535/255 + 1
      Magick::Image.constitute(frame.first.size, frame.size, 'RGB', scaled_pixels)
    end
  end
end
