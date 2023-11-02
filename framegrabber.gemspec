# frozen_string_literal: true

require_relative "lib/framegrabber/version"

Gem::Specification.new do |spec|
  spec.name = "framegrabber"
  spec.version = Framegrabber::VERSION
  spec.authors = ["Krzysztof Hasiński"]
  spec.email = ["krzysztof.hasinski@gmail.com"]

  spec.summary = "Uses OpenCV to grab frames from cameras"
  spec.description = "Allows for capturing images easily"
  spec.homepage = "https://github.com/khasinski/framegrabber"
  spec.license = "MIT"
  spec.required_ruby_version = ">= 2.7.0"

  spec.metadata["homepage_uri"] = spec.homepage
  spec.metadata["source_code_uri"] = "https://github.com/khasinski/framegrabber"

  # Specify which files should be added to the gem when it is released.
  # The `git ls-files -z` loads the files in the RubyGem that have been added into git.
  spec.files = Dir.chdir(File.expand_path(__dir__)) do
    `git ls-files -z`.split("\x0").reject do |f|
      (f == __FILE__) || f.match(%r{\A(?:(?:bin|test|spec|features)/|\.(?:git|travis|circleci)|appveyor)})
    end
  end
  spec.require_paths = ["lib"]
  spec.extensions = ["ext/grab_frame_ext/extconf.rb"]

  spec.add_development_dependency "rake-compiler", "~> 1.0"
  spec.add_dependency "pkg-config", "~> 1.4"
  spec.add_dependency "rmagick", ">= 4", "< 6"
end
