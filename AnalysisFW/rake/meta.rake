rule '.meta.json' => [proc {|trgt| trgt.sub(/\.meta\.json$/, '.txt')}] do |t|
  sample = File.basename(t.source).split('.')[0]
  mc = '--mc-mode'
  if sample.start_with? 'data'
    mc = ''
  end
  sh "compute_meta.py #{t.source} #{t.name} #{mc}"
end

task :getmeta => Dir.glob("#{ENV['URA_PROJECT']}/inputs/#{ENV['jobid']}/*.txt").map{|x| x.sub('.txt','.meta.json')}

rule '.lumi' => '.meta.json' do |t|
  sample = File.basename(t.source).split('.')[0]
  if sample.start_with? 'data'
    puts "WARNING data lumi and PU distribution still to be computed"
  else
    sh "get_mc_lumi.py #{t.source} #{ENV['URA_PROJECT']}/samples.json > #{t.name}"
  end  
end

task :getlumi => Dir.glob("#{ENV['URA_PROJECT']}/inputs/#{ENV['jobid']}/*.txt").map{|x| x.sub('.txt','.lumi')}
