# frozen_string_literal: true

require "bundler/gem_tasks"
require "rspec/core/rake_task"

RSpec::Core::RakeTask.new(:spec)

task default: :spec
task test: :compile

require "rake/extensiontask"
Rake::ExtensionTask.new("grab_frame_ext")
